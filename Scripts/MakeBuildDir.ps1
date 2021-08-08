# script to use cmake to generate the Pipeline

# Calling: MakeBuildDir

Function makeBuildDir
{
    $thisDir = $script:MyInvocation.MyCommand.Path
    $projectDir = $thisDir + "/../../"
    $buildDir = $projectDir + "/builds/"

    cd $projectDir
    cmake -S $projectDir -B $buildDir
}

makeBuildDir