$Env:CONDA_EXE = "/home/igor/Документы/cube_istaller/venv_python/bin/conda"
$Env:_CE_M = ""
$Env:_CE_CONDA = ""
$Env:_CONDA_ROOT = "/home/igor/Документы/cube_istaller/venv_python"
$Env:_CONDA_EXE = "/home/igor/Документы/cube_istaller/venv_python/bin/conda"
$CondaModuleArgs = @{ChangePs1 = $True}
Import-Module "$Env:_CONDA_ROOT\shell\condabin\Conda.psm1" -ArgumentList $CondaModuleArgs

Remove-Variable CondaModuleArgs