#!/bin/bash

VERSION=$(cd StallardOS/ && git rev-list --count master)
VERSION=$(echo "${VERSION} / 10" | bc)
VERSION_TEXT="#pragma once\n\n#define STOS_VERSION ${VERSION}U"
echo -e $VERSION_TEXT > StallardOS/lib/OS/StallardOSVersion.hpp