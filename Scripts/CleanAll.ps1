# script to use cmake to generate the Factory

# Calling: CleanAll.ps1

Function cleanAll
{
    $thisDir = $script:MyInvocation.MyCommand.Path
    $buildDir = $thisDir + "/../../builds/"

    $config = $args[0]
    $remaingingArgs = $args[1..($args.length -1 )]

    cmake --build $buildDir --verbose --target clean
}

cleanAll $args