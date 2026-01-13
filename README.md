# DevOps C Calculator Project

This repository contains a simple C application (Calculator) designed to demonstrate CI/CD concepts using Jenkins.

## Project Structure
- `src/`: Source code (`main.c`, `utils.c`, `utils.h`).
- `tests/`: Unit tests (`test_utils.c`).
- `Makefile`: Build automation tool.

## Local Development
Before working on the pipeline, you should understand how to build and test the application locally.

### Prerequisites
- GCC Compiler
- Make

## Install gcc and make using the commands 
```bash
apt install gcc make
```

### Build
To compile the application:
```bash
make build
```
This produces an executable named `app`.

### Run
```bash
./app add 5 3
# Output: 8

./app sub 10 4
# Output: 6
```

### Test
To run unit tests:
```bash
make test
```
This compiles the test runner and asserts that the utility functions work correctly.

### Release (Tagging)
To simplify creating git tags for releases, a helper target is provided:
```bash
make release VERSION=v1.0.0
```
This commands creates a git tag and pushes it to the remote repository.

---

## Assignment: Jenkins Pipeline

Your task is to generate a **Declarative Jenkins Pipeline** that automates the build, test, and release process.

### Requirements
Create a `Jenkinsfile` in the root of the repository with the following specifications:

1.  **Agent**: Use `any` or a suitable Docker agent with C tools installed.
2.  **Stages**:
    *   **Build**: Execute the make target to compile the code.
    *   **Test**: Execute the make target to run unit tests.
    *   **Deploy**: Archive the produced artifact (`app`).
3.  **Versioning**:
    *   Implement logic to handle artifact versioning.
    *   **Release Builds**: If the build is triggered by a Git Tag (e.g., `v1.0.0`), valid `env.TAG_NAME`, rename the artifact to `app-<TAG_NAME>`.
    *   **Dev Builds**: For normal branches, rename the artifact to include the branch name and build number (e.g., `app-<BRANCH>-<BUILD_NUM>`).

### Expected Outcome
- When you push a commit, Jenkins should build, test, and archive a dev artifact.
- When you create a release tag (`make release VERSION=v1.0.1`), Jenkins should build, test, and archive a release artifact (e.g., `app-v1.0.1`).
