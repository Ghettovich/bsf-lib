pipeline {
  agent any
  stages {
    stage('Clean') {
      steps {
        dir("build") {
          deleteDir();
        }
      }
    }
    stage('Configure') {
      steps {
        checkout poll: false, scm: [$class: 'GitSCM', branches: [[name: 'origin/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'WipeWorkspace']], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '51e3bd50-468c-413f-97a7-ba5b72c9727c', url: 'https://github.com/Ghettovich/bsf-lib']]]
      }
    }
    stage('Build') {
      steps {
        cmake installation: 'InSearchPath', workingDir: 'build'
        cmakeBuild buildDir: 'build', buildType: 'Debug', cleanBuild: true, cmakeArgs: '-DCMAKE_CXX_FLAGS=--coverage -DCMAKE_C_FLAGS=--coverage', installation: 'InSearchPath', steps: [[withCmake: true]]
      }
    }
    stage('Test') {
      steps {
        dir('build') {
          ctest arguments: '-T Test --no-compress-output', installation: 'InSearchPath'
        }
      }
    }
  }
  post {
     always {
      xunit([QtTest(deleteOutputFiles: true, failIfNotNew: true, pattern: 'build/Temporary/LastTest_*.log', skipNoTestFiles: false, stopProcessingIfError: true)])
    }
  }
}