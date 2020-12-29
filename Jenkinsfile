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
    stage('Build') {
      steps {
        checkout poll: false, scm: [$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'CleanBeforeCheckout']], submoduleCfg: [], userRemoteConfigs: [[credentialsId: 'd29ef267-2eb6-437f-9b79-b1cb33a6a464', name: 'origin', url: 'https://github.com/Ghettovich/bsf-lib']]]
        cmake installation: 'InSearchPath', workingDir: 'build'
        cmakeBuild buildDir: 'build', buildType: 'Debug', cleanBuild: true, cmakeArgs: '-DCMAKE_CXX_FLAGS=--coverage -DCMAKE_C_FLAGS=--coverage', installation: 'InSearchPath', steps: [[withCmake: true]]
      }
    }
    stage('Test') {
      steps {
        dir('build') {
          ctest arguments: '-T test -D Nightly Test --no-compress-output', installation: 'InSearchPath'
        }
      }
    }
  }
}