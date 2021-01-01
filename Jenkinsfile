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
        checkout poll: false, scm: [$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[url: 'git@github.com:Ghettovich/bsf-lib.git']]]
      }
    }
    stage('Build') {
      steps {
        cmake installation: 'InSearchPath', workingDir: 'build'
        cmakeBuild buildDir: 'build', buildType: 'Debug', cleanBuild: true, cmakeArgs: '''-DCMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage"
        -DCMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage"
        -DCMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage"''', installation: 'InSearchPath', steps: [[withCmake: true]]
      }
    }
    stage('Test') {
      steps {
        dir('build') {
          ctest arguments: '-D Experimental', installation: 'InSearchPath'
          ctest arguments: '-D Nightly', installation: 'InSearchPath'
        }
      }
    }
  }
  post {
     always {
       xunit([CTest(deleteOutputFiles: true, failIfNotNew: true, pattern: 'build/Testing/**/*.xml', skipNoTestFiles: false, stopProcessingIfError: true)])
    }
  }
}