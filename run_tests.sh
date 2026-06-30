#!/usr/bin/env bash

set -euo pipefail

PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

cmake -S "${PROJECT_DIR}" -B "${BUILD_DIR}"
cmake --build "${BUILD_DIR}" --target search_engine_tests

cd "${PROJECT_DIR}"
exec "${BUILD_DIR}/search_engine_tests" "$@"
