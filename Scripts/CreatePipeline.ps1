# script to use cmake to generate the Pipeline

# Calling: CreatePipeline.ps1 <config> <args>

Function createPipeline
{
    $thisDir = $script:MyInvocation.MyCommand.Path
    $buildDir = $thisDir + "/../../builds/"

    $config = $args[0]
    $remaingingArgs = $args[1..($args.length -1 )]

    cmake --build $buildDir --config $config --target Pipeline $remaingingArgs
}

createPipeline $args