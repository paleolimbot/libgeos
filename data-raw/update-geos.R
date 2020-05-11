
library(tidyverse)

# download S2
source_url <- "http://download.osgeo.org/geos/geos-3.8.1.tar.bz2"
curl::curl_download(source_url, "data-raw/geos-source.tar.bz2")
untar("data-raw/geos-source.tar.bz2", exdir = "data-raw")

# make sure the dir exists
geos_dir <- list.files("data-raw", "^geos-[0-9.]+", include.dirs = TRUE, full.names = TRUE)
stopifnot(dir.exists(geos_dir), length(geos_dir) == 1)
src_dir <- file.path(geos_dir, "src/s2")

# headers live in inst/include
# keeping the directory structure means that
# we don't have to update any source files (beause of header locations)
headers <- tibble(
  path = list.files(
    file.path(geos_dir, "include", "geos"), "\\.(h)$",
    full.names = TRUE,
    recursive = TRUE
  ),
  final_path = str_replace(path, ".*?geos/", "inst/include/geos/")
)

# If source files are in src/ with no subdirectories
# We can use the built-in R Makefile with few modifications
# in Makevars. Here, we replace "/" with "__"
source_files <- tibble(
  path = list.files(file.path(geos_dir, "src"), "\\.cpp$", full.names = TRUE, recursive = TRUE),
  final_path = str_replace(path, ".*?src/", "src/") %>%
    str_replace_all("/", "__") %>%
    str_replace("src__", "src/")
)

# clean source dir
current_source_files <- tibble(
  path = list.files("src", "\\.(h|hpp|cpp|o|cc)$", full.names = TRUE, recursive = TRUE)
) %>%
  filter(!str_detect(path, "^src/(libgeos-|Rcpp|Makevars)"))

unlink(current_source_files$path)
unlink("inst/include/geos", recursive = TRUE)

# create destination dirs
dest_dirs <- c(
  headers %>% pull(final_path),
  source_files %>% pull(final_path)
) %>%
  dirname() %>%
  unique()
dest_dirs[!dir.exists(dest_dirs)] %>% walk(dir.create, recursive = TRUE)

# copy source files
stopifnot(
  file.copy(headers$path, headers$final_path),
  file.copy(source_files$path, source_files$final_path),

  # there is one errant header file in the sources that is needed for compile
  file.copy(
    file.path(geos_dir, "src/operation/valid/IndexedNestedRingTester.h"),
    "src/IndexedNestedRingTester.h"
  )
)

# reminders about manual modifications that are needed
# for build/CMD check to succeed
print_next <- function() {
  cli::cat_rule("Manual modifications")
  cli::cat_bullet(
    "inst/include/s2/base/logging.h: ",
    "Added a 'getter' for `S2LogMessage::_severity` (silences -Wunused_member)"
  )

  cli::cat_bullet("Replace `abort()` with `cpp_compat_abort()`")
  cli::cat_bullet("Replace `cerr`/`cout` with `cpp_compat_cerr`/`cpp_compat_cout`")
  cli::cat_bullet("Replace `srandom()` with `cpp_compat_srandom()`")
  cli::cat_bullet("Replace `random()` with `cpp_compat_random()`")
}

print_next()
