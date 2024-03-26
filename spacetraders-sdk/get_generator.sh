#!/bin/bash

mkdir -p openapitools
curl https://raw.githubusercontent.com/OpenAPITools/openapi-generator/master/bin/utils/openapi-generator-cli.sh > ./openapitools/openapi-generator-cli
chmod u+x ./openapitools/openapi-generator-cli
