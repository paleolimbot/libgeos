
library(tidyverse)

# download GEOS
source_url <- "http://download.osgeo.org/geos/geos-3.9.1.tar.bz2"
curl::curl_download(source_url, "data-raw/geos-source.tar.bz2")
untar("data-raw/geos-source.tar.bz2", exdir = "data-raw")

# make sure the dir exists
geos_dir <- list.files("data-raw", "^geos-[0-9.]+", include.dirs = TRUE, full.names = TRUE)
stopifnot(dir.exists(geos_dir), length(geos_dir) == 1)
src_dir <- file.path(geos_dir, "src")

# one way to make sure that geos_c.h is built is to run ./configure
withr::with_dir(
  geos_dir,
  system("./configure")
)

# headers live in inst/include
# keeping the directory structure means that
# we don't have to update any source files (because of header locations)
headers <- tibble(
  path = list.files(
    file.path(geos_dir, "include", "geos"), "\\.(h|inl)$",
    full.names = TRUE,
    recursive = TRUE
  ),
  final_path = str_replace(path, ".*?geos/", "src/geos_include/geos/")
)

# If source files are in src/ with no subdirectories
# We can use the built-in R Makefile with few modifications
# in Makevars. Here, we replace "/" with "__"
source_files <- tibble(
  path = list.files(file.path(geos_dir, "src"), "\\.cpp$", full.names = TRUE, recursive = TRUE),
  final_path = str_replace(path, ".*?src/", "src/geos/")
)

# remove current source and header files
unlink("src/geos_include/geos", recursive = TRUE)
unlink("src/geos_include/geos_c.h")
unlink("src/geos", recursive = TRUE)

# create destination dirs
dest_dirs <- c(
  headers %>% pull(final_path),
  source_files %>% pull(final_path)
) %>%
  dirname() %>%
  unique() %>%
  sort()
dest_dirs[!dir.exists(dest_dirs)] %>% walk(dir.create, recursive = TRUE)

# copy source files
stopifnot(
  file.copy(headers$path, headers$final_path),
  file.copy(source_files$path, source_files$final_path),

  # there is one errant header file in the sources that is needed for compile
  file.copy(
    file.path(geos_dir, "src/operation/valid/IndexedNestedRingTester.h"),
    "src/geos/operation/valid/IndexedNestedRingTester.h"
  ),

  # also need to copy the C API cpp and header
  file.copy(
    file.path(geos_dir, "capi/geos_c.h"),
    "src/geos_include/geos_c.h"
  ),
  file.copy(
    file.path(geos_dir, "capi/geos_ts_c.cpp"),
    "src/geos/geos_ts_c.cpp"
  )
)

# need to update objects because we've placed the geos bits in subfolders
objects <- list.files("src", pattern = "\\.c(pp)?$", recursive = TRUE, full.names = TRUE) %>%
  gsub("\\.c(pp)?$", ".o", .) %>%
  gsub("src/", "", .) %>%
  paste("    ", ., "\\", collapse = "\n") %>%
  gsub("\\\\\\s*$", "", .)

clipr::write_clip(objects)

#' Reminders about manual modifications that are needed
#' - inst/include/geos/algorithm/ttmathuint.h: Remove pragmas suppressing diagnostics
#' - inst/include/geos/algorithm/ttmathuint.h: Remove non-portable pragmas
#' - noding__snapround__MCIndexSnapRounder.cpp: Replace cerr with cpp_compat_cerr
#' - src/operation__overlay__ElevationMatrix.cpp: Replace cerr with cpp_compat_cerr
#' - src/simplify__TopologyPreservingSimplifier.cpp: Replace cerr with cpp_compat_cerr
#' - src/util__Profiler.cpp: Replace cerr with cpp_compat_cerr
#' - Update OBJECTS in Makevars (copied to clipboard)
#' - Update exported C API using update-libgeos-api.R
