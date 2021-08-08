# script to use cmake to generate the Factory

# Calling: CreateFactory.ps1 <config> <args>

Function createFactory
{
    $thisDir = $script:MyInvocation.MyCommand.Path
    $buildDir = $thisDir + "/../../builds/"

    $config = $args[0]
    $remaingingArgs = $args[1..($args.length -1 )]

    cmake --build $buildDir --config $config --target Factory $remaingingArgs
}

createFactory $args