New-Item -ItemType Directory -Force -Path mono | Out-Null
Get-ChildItem -Filter "*.wav" | ForEach-Object {
  ffmpeg -i $_.FullName -ac 1 (Join-Path "mono" $_.Name)
}