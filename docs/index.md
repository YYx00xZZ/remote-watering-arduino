## Project layout

    mkdocs.yml           # The configuration file.
    docs/
        index.md         # The documentation homepage.
        ...              # Other markdown pages, images and other files.
    examples/            # direktoriqta sudurja gotovi za kachvane primeri
        example.ino      # Arduino IDE sketch
        ...
    libs/                # Vsichki nujni biblioteki v zip arhivi
        externalLib.zip  # naprimer
        ...
    sketches/            # Sudurja programite napisani ot nas
        sketch.ino
        ...

## Commands

* `mkdocs new [dir-name]` - Create a new project.
* `mkdocs serve` - Start the live-reloading docs server.
* `mkdocs build` - Build the documentation site.
* `mkdocs -h` - Print help message and exit.