# DevOps C Calculator Server

This repository contains a simple C-based HTTP Server designed to demonstrate CI/CD concepts using Jenkins.

## Project Structure
- `src/`: Source code (`server.c`, `utils.c`, `utils.h`).
- `tests/`: Unit tests (`test_utils.c`).
- `Makefile`: Build automation tool.

## Local Development
### Prerequisites
- GCC Compiler
- Make

### Build
To compile the server:
```bash
make server
```
This produces an executable named `server`.

### Run
To start the server:
```bash
./server
```
It listens on **port 8080**.

### API Usage
Use `curl` or a browser to access the math functions:
- **Add**: `http://localhost:8080/add?a=10&b=5` -> Returns 15
- **Sub**: `http://localhost:8080/sub?a=10&b=5` -> Returns 5
- **Mul**: `http://localhost:8080/mul?a=10&b=5` -> Returns 50
- **Div**: `http://localhost:8080/div?a=10&b=5` -> Returns 2

### Test
To run unit tests:
```bash
make test
```

---

## Assignment: Jenkins Pipeline

Your task is to generate a **Declarative Jenkins Pipeline** that automates the build, test, and release process.

### Requirements
1.  **Agent**: Use `any`.
2.  **Stages**:
    *   **Build**: Execute `make server`.
    *   **Test**: Execute `make test`.
    *   **Deploy**: Archive the produced artifact (`server`).
3.  **Versioning**:
<<<<<<< Updated upstream
    *   Implement logic to handle artifact versioning.
    *   **Release Builds**: If the build is triggered by a Git Tag (e.g., `v1.0.0`), valid `env.TAG_NAME`, rename the artifact to `app-<TAG_NAME>`.
    *   **Dev Builds**: For normal branches, rename the artifact to include the branch name and build number (e.g., `app-<BRANCH>-<BUILD_NUM>`).
=======
    *   **Release Builds**: If the build is triggered by a Git Tag (e.g., `v1.0.0`), valid `git describe --tags`, rename the artifact to `server-<TAG_NAME>`.
    *   **Dev Builds**: For normal branches, rename the artifact to `server-dev-<BUILD_NUM>`.
>>>>>>> Stashed changes

### Release
To create a release:
```bash
make release VERSION=v1.0.0
```
