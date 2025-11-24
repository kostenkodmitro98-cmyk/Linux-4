pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git url: 'http://192.168.0.202:3000/Dmytro/Linux-4.git', credentialsId: 'linux-kursovs'
            }
        }
        
        stage('Build') {
            steps {
                // Крок для збірки проекту з Visual Studio
                // Встановіть правильні шляхи до рішення/проекту та параметри MSBuild
                bat '"C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin" test_repos.sln /t:Build /p:Configuration=Release'
            }
        }

        stage('Test') {
            steps {
                // Команди для запуску тестів
                bat "x64\\Debug\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }

    post {
    always {
        // Publish test results using the junit step
         // Specify the path to the XML test result files
    }
}
}