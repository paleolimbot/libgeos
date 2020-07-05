
This is a new submission of a port of the Open Source Geometry Engine (GEOS) to the R package framework. This package does not link to system GEOS; it contains a copy of the latest version and exports the C API. This is desirable for several reasons: first, it enables a more consistent version guarnatee so that the latest GEOS features can be used in compiled code. This can be a problem on Linux distributions whose package repository contains an outdated version of GEOS (if it provides one at all). A consistent (and recent) GEOS version is desirable for both stability and reproducibility. Second, it enables the use of GEOS in environments where a user does not have administrator access. Finally, GEOS is licensed under the LGPL, which generally allows dynamic linking from software with other licenses. Packaging the GEOS sources as they are in this package makes license compliance clearer.

## Test environments

* local R installation, MacOS R 4.0.1
* GitHub actions: MacOS, Windows, Ubuntu 16.04 (R 3.6.3 & R 4.0.1)
* win-builder (devel)
* `rhub::check_for_cran()`

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
