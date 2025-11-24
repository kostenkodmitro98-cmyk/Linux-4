pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', 
                url: 'https://github.com/kostenkodmitro98-cmyk/Linux-4.git'
            }
        }
        
        stage('NuGet Restore') {
            steps {
                bat ' "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln /t:restore /p:Configuration=Debug /p:Platform=x64 /p:WindowsTargetPlatformVersion=10.0 '
            }
        }
        
        stage('Build') {
            steps {
                bat ' "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln /p:Configuration=Debug /p:Platform=x64 /p:WindowsTargetPlatformVersion=10.0 '
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
            junit 'test_report.xml'
        }
    }
}
