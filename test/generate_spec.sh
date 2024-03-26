#!/bin/bash

#  -i "https://stoplight.io/api/v1/projects/spacetraders/spacetraders/nodes/reference/SpaceTraders.json?fromExportButton=true&snapshotType=http_service&deref=optimizedBundle" \
# openapi-generator generate \
# npx @openapitools/openapi-generator-cli generate \
./openapitools/openapi-generator-cli generate \
 -i spacetraders_spec.yaml \
 -o packages/spacetraders-sdk \
 -g lua \
 --additional-properties=npmName="spacetraders-sdk" \
 --additional-properties=npmVersion="8.5.1" \
 --additional-properties=supportsES6=true \
 --additional-properties=withSeparateModelsAndApi=true \
 --additional-properties=modelPackage="models" \
 --additional-properties=apiPackage="api"

# npx @openapitools/openapi-generator-cli generate -i spacetraders_spec.yaml -g cpprest -o /tmp/test/
# openapi-generator-cli generate -i ./spacetraders_spec.yaml -g lua -o /tmp/test/
