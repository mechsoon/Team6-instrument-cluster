#!/bin/bash

# Variables
GITHUB_USER="mechsoon"
GITHUB_REPO="Team6-instrument-cluster"
GITHUB_TOKEN="YOURGITHUBTOKEN"
ARTIFACT_NAME="build-artifacts"
DOWNLOAD_DIR="/home/team6/artifacts"
TMP_DIR="/tmp/github_artifacts"

# Create necessary directories
mkdir -p $DOWNLOAD_DIR
mkdir -p $TMP_DIR

# Get the latest successful workflow run ID for the main branch
workflow_run_id=$(curl -s -H "Authorization: token $GITHUB_TOKEN" \
  "https://api.github.com/repos/$GITHUB_USER/$GITHUB_REPO/actions/runs?branch=main&status=success" \
  | jq -r '.workflow_runs[0].id')

# Check if the workflow_run_id is null or empty
if [ -z "$workflow_run_id" ]; then
  echo "Error: Failed to fetch workflow run ID."
  exit 1
fi

# Get the artifact download URL
artifact_url=$(curl -s -H "Authorization: token $GITHUB_TOKEN" \
  "https://api.github.com/repos/$GITHUB_USER/$GITHUB_REPO/actions/runs/$workflow_run_id/artifacts" \
  | jq -r --arg ARTIFACT_NAME "$ARTIFACT_NAME" '.artifacts[] | select(.name == $ARTIFACT_NAME) | .archive_download_url')

# Check if the artifact_url is null or empty
if [ -z "$artifact_url" ]; then
  echo "Error: Failed to fetch artifact URL."
  exit 1
fi

# Download the artifact
curl -L -H "Authorization: token $GITHUB_TOKEN" -o $TMP_DIR/${ARTIFACT_NAME}.zip $artifact_url

# Check if the artifact was downloaded
if [ ! -f "$TMP_DIR/${ARTIFACT_NAME}.zip" ]; then
  echo "Error: Failed to download artifact."
  exit 1
fi

# Remove old artifacts
rm -rf $DOWNLOAD_DIR/*

unzip -o $TMP_DIR/${ARTIFACT_NAME}.zip -d $DOWNLOAD_DIR

# List contents of the download directory
echo "Contents of $DOWNLOAD_DIR:"
ls -la $DOWNLOAD_DIR

# Set execute permission for InstrumentCluster
if [ -f "$DOWNLOAD_DIR/InstrumentCluster" ]; then
  chmod +x $DOWNLOAD_DIR/InstrumentCluster
  echo "Execute permission set for InstrumentCluster"
else
  echo "Warning: InstrumentCluster executable not found in the artifacts."
fi

# Check for QML files
if ls $DOWNLOAD_DIR/*.qml 1> /dev/null 2>&1; then
  echo "QML files found in the artifacts:"
  ls $DOWNLOAD_DIR/*.qml
else
  echo "Warning: QML files not found in the artifacts."
fi

# Check for QRC files
if ls $DOWNLOAD_DIR/*.qrc 1> /dev/null 2>&1; then
  echo "QRC files found in the artifacts:"
  ls $DOWNLOAD_DIR/*.qrc
else
  echo "Warning: QRC files not found in the artifacts."
fi

# Ensure QML files are in the correct location
if [ -f "$DOWNLOAD_DIR/main.qml" ]; then
  echo "QML files found in the artifacts."
else
  echo "Warning: QML files not found in the artifacts."
fi

# Clean up temporary files
rm -rf $TMP_DIR

echo "Artifacts updated successfully."
