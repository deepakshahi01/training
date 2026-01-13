pipeline{
	agent any
		stages{
			stage("build"){
				steps{
					echo "building"
					sh 'make build'	
				}
			}
			stage("test"){
				steps{
					echo "testing"
					sh 'make test'	
				}
			}
			stage("deploy"){
				steps{
					echo "deploying"
					archiveArtifacts artifacts: "app", fingerprint:true	
				}
			}
	}
}
