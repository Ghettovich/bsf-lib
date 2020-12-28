pipeline {
  agent any
  triggers {
    githubPush()
  }
  stages {
    stage('Configure') {
      steps {
        dir('build') {
          sh 'cmake -DCMAKE_CXX_FLAGS=--coverage -DCMAKE_C_FLAGS=--coverage ../'
        }
      }
    }
    stage('Build') {
      steps {
        dir('build') {
          sh 'cmake --build .'
        }
      }
    }
    stage('Test') {
      steps {
        dir('build') {
          sh 'ctest -T test -D Experimental Test  --no-compress-output'
        }
      }
    }
  }
  post {
    always {
      // Archive the CTest xml output
      archiveArtifacts (
        artifacts: 'build/Testing/**/*.xml',
        fingerprint: true
      )

      // Process the CTest xml output with the xUnit plugin
      xunit (
        testTimeMargin: '3000',
        thresholdMode: 1,
        thresholds: [
          skipped(failureThreshold: '0'),
          failed(failureThreshold: '0')
        ],
      tools: [CTest(
          pattern: 'build/Testing/**/*.xml',
          deleteOutputFiles: true,
          failIfNotNew: false,
          skipNoTestFiles: true,
          stopProcessingIfError: true
        )]
      )

      // Clear the source and build dirs before next run
      deleteDir()
    }
  }
}