Function clangFormatDir
{
    $rootDir = $args[0]
    echo "calling clang-format for all files under $rootDir"
    $files = Get-ChildItem -Path $rootDir -Recurse | where {$_.name -match '^.*\.(cpp|h)$'}

    foreach ($file in $files){
        $fileName = $file.FullName
        echo $fileName
        clang-format $fileName -i
    }
}

Function clangFormatApplication
{
    $thisDir = $script:MyInvocation.MyCommand.Path
    $applicationDir = $thisDir + "/../../ThePlant/"
    ls $applicationDir

    clangFormatDir $applicationDir/Factory
    clangFormatDir $applicationDir/Materials
    clangFormatDir $applicationDir/Pipeline
    clangFormatDir $applicationDir/Product
    clangFormatDir $applicationDir/Resources
}

clangFormatApplication