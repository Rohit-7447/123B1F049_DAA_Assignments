pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Compiling the Java code...'
                // For a real project: bat 'javac Main.java'
            }
        }
        stage('Test') {
            steps {
                echo 'Running Unit Tests...'
                // For a real project: bat 'java Main'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying to Production Server...'
            }
        }
    }
}
