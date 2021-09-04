package main

import (
  "fmt"
  "io/fs"
  "os"
  "path/filepath"
)

func main() {
  rootFS := os.DirFS("./testdir")
  fmt.Println("fs.WalkDir")
  err := fs.WalkDir(rootFS, ".", walkDirFunc)
  if err != nil {
    fmt.Printf("error with fs.WalkDir: %v\n", err)
  }
  fmt.Println("\nfilepath.WalkDir")
  err = filepath.WalkDir("./testdir", walkDirFunc)
  if err != nil {
    fmt.Printf("error with filepath.WalkDir: %v\n", err)
  }
  fmt.Println("\nfilepath.Walk")
  err = filepath.Walk("./testdir", walkFunc)
  if err != nil {
    fmt.Printf("error with filepath.Walk: %v\n", err)
  }
}

func walkDirFunc(path string, d fs.DirEntry, err error) error {
  if err != nil {
    return err
  }
  fmt.Printf("Path: %s, Name: %s\n", path, d.Name())
  return nil
}

func walkFunc(path string, info fs.FileInfo, err error) error {
  if err != nil {
    return err
  }
  fmt.Printf("Path: %s, Name: %s\n", path, info.Name())
  return nil
}
