while true; do
  change=$(inotifywait -e close_write,moved_to,create .)
  change=${change#./ * }
  if [ "$change" = "supersonic_storage.tex" ]; then bash ./compile_images.sh; pdflatex supersonic_storage.tex; fi
done
