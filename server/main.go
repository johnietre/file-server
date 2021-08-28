package main

import (
  "fmt"
)

func main() {
  ftree, err := NewFileTree("./tests")
  if err != nil {
    panic(err)
  }
  readDir(ftree.root)
}

func readDir(de *DirEntry) {
  fmt.Println(de.Path())
  for _, child := range de.children {
    fmt.Println(child.Path())
    if child.isDir {
      readDir(child)
    }
  }
}
