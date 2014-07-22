#!/bin/bash

set -e

# Inspect binary.
if [ $platform == "linux" ]; then
    ldd ./build/Release/_s2.node
else
    otool -L ./build/Release/_s2.node
fi

COMMIT_MESSAGE=$(git show -s --format=%B $TRAVIS_COMMIT | tr -d '\n')

if test "${COMMIT_MESSAGE#*'[publish binary]'}" != "$COMMIT_MESSAGE"
    then

    npm install aws-sdk
    ./node_modules/.bin/node-pre-gyp package testpackage
    ./node_modules/.bin/node-pre-gyp publish info

    rm -rf build
    npm install --fallback-to-build=false
    npm test

    npm install aws-sdk
    node-pre-gyp info
fi
