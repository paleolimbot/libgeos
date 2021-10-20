
library(tidyverse)

# download GEOS
source_url <- "http://download.osgeo.org/geos/geos-3.10.0.tar.bz2"
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

# headers live in src/geos_include (we don't want them exposed
# for packages LinkingTo)
headers <- tibble(
  path = list.files(
    file.path(geos_dir, "include", "geos"), "\\.(h|inl)$",
    full.names = TRUE,
    recursive = TRUE
  ),
  final_path = str_replace(path, ".*?geos/", "src/geos_include/geos/")
)

# source files live in src/geos
source_files <- tibble(
  path = list.files(file.path(geos_dir, "src"), "\\.cpp$", full.names = TRUE, recursive = TRUE),
  final_path = str_replace(path, ".*?src/", "src/geos/")
)

# remove current source and header files
unlink("src/geos_include/geos", recursive = TRUE)
unlink("src/geos_include/ryu", recursive = TRUE)
unlink("src/geos_include/geos_c.h")
unlink("src/geos", recursive = TRUE)
unlink("src/ryu", recursive = TRUE)

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

  # also need to copy the C API cpp and header
  file.copy(
    file.path(geos_dir, "capi/geos_c.h"),
    "src/geos_include/geos_c.h"
  ),
  file.copy(
    file.path(geos_dir, "capi/geos_ts_c.cpp"),
    "src/geos/geos_ts_c.cpp"
  ),

  # need the custom JSON includer
  # using the modified version from libproj that already works with
  # CRAN specs on all platforms (so don't copy json.hpp)
  file.copy(
    file.path(geos_dir, "include/geos/vend/include_nlohmann_json.hpp"),
    "src/geos_include/geos/vend/include_nlohmann_json.hpp"
  ),

  # need to copy ryu library
  file.copy(
    file.path(geos_dir, "src/deps/ryu/d2s.c"),
    "src/ryu/d2s.c"
  ),
  file.copy(
    file.path(
      geos_dir, "src/deps/ryu",
      c(
        "common.h", "d2fixed_full_table.h",
        "d2s_full_table.h", "d2s_intrinsics.h",
        "digit_table.h", "ryu.h"
      )
    )
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
#' - noding__snapround__MCIndexSnapRounder.cpp: Replace cerr with cpp_compat_cerr
#' - src/operation__overlay__ElevationMatrix.cpp: Replace cerr with cpp_compat_cerr
#' - src/simplify__TopologyPreservingSimplifier.cpp: Replace cerr with cpp_compat_cerr
#' - src/util__Profiler.cpp: Replace cerr with cpp_compat_cerr
#' - update include in include_nlohmann_json.hpp to point to custom nlohmann_json.hpp
#' - Update OBJECTS in Makevars (copied to clipboard)
#' - Update exported C API using update-libgeos-api.R
