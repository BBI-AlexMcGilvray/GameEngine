# script to use cmake to generate the Product

# Calling: CreateProduct.ps1 <config> <args>

Function createProduct
{
    $thisDir = $script:MyInvocation.MyCommand.Path
    $buildDir = $thisDir + "/../../builds/"

    $config = $args[0]
    $remaingingArgs = $args[1..($args.length -1 )]

    cmake --build $buildDir --config $config --target Product $remaingingArgs
}

createProduct $args