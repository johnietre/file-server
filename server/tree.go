package main

import (
  "errors"
  "io/fs"
  "os"
)

type dirEntry struct {
  name string
  parent *dirEntry
  children []*dirEntry
  isDir bool
  lastMod int64
}

type FileTree struct {
  //
}

func NewFileTree(rootPath string) (*FileTree, error) {
  // Check to make sure the root is a directory
  info, err := os.Stat(rootPath)
  if err != nil {
    return nil, err
  } else if !info.IsDIr() {
    return nil, errors.New("root is not a directory")
  }
  // Create the root directory entry
  root := dirEntry{
    name: info.Name(),
    parent: nil,
    children: make([]*dirEntry, 1),
    isDir: true,
    lastMod: info.ModTime().Unix(),
  }
  // Create the filesystem and walk through it
  rootFS := os.DirFS(rootPath)
  err := fs.WalkDir(rootFS, ".", func(path string, d fs.DirEntry, err error) error {
    if err != nil {
      return err
    }
  })
  if err != nil {
    return nil, err
  }
}
