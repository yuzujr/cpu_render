#!/usr/bin/env bash
set -euo pipefail

out_dir="output"
tmp_dir="output/tmp"

shopt -s nullglob
ppms=("${tmp_dir}"/output-*.ppm)
shopt -u nullglob

play() {
  local file="$1"
  setsid -f mpv "$file" --loop >/dev/null 2>&1
  echo "Playing: $file"
}

if (( ${#ppms[@]} > 0 )); then
  ts="$(date +%Y%m%d-%H%M%S)"
  out_mp4="${out_dir}/output-${ts}.mp4"

  ffmpeg -y -framerate 60 -i "${tmp_dir}/output-%03d.ppm" -pix_fmt yuv420p "${out_mp4}"

  play "${out_mp4}"

  rm -f "${tmp_dir}/"*.ppm
  echo "Cleared: ${tmp_dir}/*.ppm"
else
  latest="$(ls -1t "${out_dir}"/output-*.mp4 2>/dev/null | head -n 1 || true)"
  if [[ -z "${latest}" ]]; then
    echo "No ppm in ${tmp_dir} and no mp4 found in ${out_dir}."
    exit 1
  fi
  play "${latest}"
fi
