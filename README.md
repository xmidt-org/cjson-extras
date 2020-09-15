# cjson-extra

Misc C-json modules.

[![Build Status](https://travis-ci.com/xmidt-org/cjson-extras.svg?branch=master)](https://travis-ci.com/xmidt-org/cjson-extras)
[![codecov.io](http://codecov.io/github/xmidt-org/cjson-extras/coverage.svg?branch=master)](http://codecov.io/github/xmidt-org/cjson-extras?branch=master)
[![Coverity](https://img.shields.io/coverity/scan/11572.svg)]("https://scan.coverity.com/projects/comcast-cjson-extras)
[![Apache V2 License](http://img.shields.io/badge/license-Apache%20V2-blue.svg)](https://github.com/xmidt-org/cjson-extras/blob/master/LICENSE.txt)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=xmidt-org_cjson-extras&metric=alert_status)](https://sonarcloud.io/dashboard?id=xmidt-org_cimplog)

# Building and Testing Instructions

```
mkdir build
cd build
cmake ..
make
make test
```

# Coding Formatter Settings

Please format pull requests using the following command to keep the style consistent.

```
astyle -A10 -S -f -U -p -D -c -xC90 -xL
```
