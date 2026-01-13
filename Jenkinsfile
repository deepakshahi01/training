pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh 'make build'
            }
        }
        stage('Test') {
            steps {
                sh 'make test'
            }
        }
        stage('Deploy') {
            steps {
                script {
                    def version = ""
                    if (env.TAG_NAME) {
                        version = env.TAG_NAME
                    } else if (env.BRANCH_NAME) {
                        version = "${env.BRANCH_NAME}-${env.BUILD_NUMBER}"
                    } else {
                        version = "dev-${env.BUILD_NUMBER}"
                    }
                    sh "mv app app-${version}"
                    archiveArtifacts artifacts: "app-${version}", fingerprint: true
                }
            }
        }
    }
}
