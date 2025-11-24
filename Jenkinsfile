pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', 
                url: 'https://github.com/kostenkodmitro98-cmyk/Linux-4.git'
            }
        }
        
        stage('Download NuGet and Google Test') {
            steps {
                // Завантажити NuGet
                bat 'curl -o nuget.exe https://dist.nuget.org/win-x86-commandline/latest/nuget.exe'
                
                // Встановити Google Test
                bat 'nuget.exe install Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn -Version 1.8.1.7 -OutputDirectory packages'
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
