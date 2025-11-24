pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', 
                url: 'https://github.com/kostenkodmitro98-cmyk/Linux-4.git'
            }
        }
        
        stage('Build') {
            steps {
                bat ' "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln /p:Configuration=Debug /p:Platform=x64 '
            }
        }

        stage('Test') {
            steps {
                bat ' "x64\\Debug\\test_repos.exe" --gtest_output="xml:test_report.xml" '
            }
        }
    }

    post {
        always {
            xunit(
                tools: [GoogleTest(pattern: 'test_report.xml')],
                healthScaleFactor: 1.0,
                thresholds: [
                    failed(failureThreshold: '0'),
                    skipped(skippedThreshold: '0')
                ]
            )
        }
    }
}
