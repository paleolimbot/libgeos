
This submission fixes warnings from the link-time optimizer, which reported naming conflicts between the C++ header types and the abstract C types used in the header API.

## Test environments

* local R installation, MacOS R 4.0.1
* GitHub actions: MacOS (R release), Windows (R oldrel and release), Ubuntu 16.04 (R release)
* win-builder (devel)
* `rhub::check_for_cran()`

## R CMD check results

* checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Dewey Dunnington <dewey@fishandwhistle.net>’

Days since last update: 3

Updated promptly at the request of CRAN, who issued a notice that the package would be removed if the check problems were not fixed.
