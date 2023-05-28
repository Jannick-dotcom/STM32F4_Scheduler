#!/bin/bash

VERSION=$(cd StallardOS/ && git rev-list --count master)
VERSION_TEXT="#pragma once\n\n#define STOS_VERSION $VERSION"
echo -e $VERSION_TEXT > StallardOS/lib/OS/StallardOSVersion.hpp