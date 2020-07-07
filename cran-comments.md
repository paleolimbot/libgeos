
Since the initial submission, the Description and Authors fields were updated at the request of CRAN to include all authors and copyright holders that have been credited in the GEOS sources.

This is a new submission of a port of the Open Source Geometry Engine (GEOS) to the R package framework. This package does not link to system GEOS; it contains a copy of the latest version and exports the C API. This is desirable for several reasons. First, it enables a more consistent version guarnatee so that the latest GEOS features can be used in R packages. This can be a problem on Linux distributions whose package repository contains an outdated version of GEOS (if it provides one at all). A consistent (and recent) GEOS version is desirable for both stability and reproducibility. Second, it enables the use of GEOS in environments where a user does not have administrator access, where installing R packages is usually allowed. Finally, GEOS is licensed under the LGPL, which generally allows dynamic linking from software with other licenses. Packaging the GEOS sources as they are in this package makes license compliance clear.

## Test environments

* local R installation, MacOS R 4.0.1
* GitHub actions: MacOS, Windows, Ubuntu 16.04 (R 3.6.3 & R 4.0.1)
* win-builder (devel)
* `rhub::check_for_cran()`

## R CMD check results

* checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Dewey Dunnington <dewey@fishandwhistle.net>’

New submission

Possibly mis-spelled words in DESCRIPTION:
  GEOS (2:37, 15:56)
  
* checking installed package size ... NOTE
  installed size is 34.2Mb
  sub-directories of 1Mb or more:
    libgeos_include   2.9Mb (there really is almost 3 Mb of header text!)
    libs             31.1Mb
