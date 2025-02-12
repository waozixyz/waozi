{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    pkg-config
    raylib
    gcc
    gdb
    ccache
    valgrind
  ];

  shellHook = ''
    echo "Inner Breeze development environment ready!"
    echo "Available commands:"
    echo "  make         - Build the project with Raylib (optimized)"
    echo "  make clean   - Clean build artifacts"
  '';
}
