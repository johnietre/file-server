package main

import (
  "errors"
  "io/ioutil"
  "log"
  "path"
  "os"
  "sync"
)

type DirEntry struct {
  name string
  parent *DirEntry
  children []*DirEntry
  isDir bool
  lastMod int64
  mtx sync.RWMutex
}

func (de *DirEntry) Path() string {
  if de.isDir {
    if de.parent == nil {
      return de.name + "/"
    }
    return de.parent.Path() + de.name + "/"
  }
  return de.parent.Path() + de.name
}

type FileTree struct {
  root *DirEntry
  rootPath string
  logger *log.Logger
  doneChan chan struct{}
}

func NewFileTree(rootPath string) (*FileTree, error) {
  var buildDir func(dirPath string, dir *DirEntry) error
  buildDir = func(dirPath string, dir *DirEntry) error {
    // Get the directory entries for the given path
    entries, err := ioutil.ReadDir(dirPath)
    if err != nil {
      return err
    }
    // Add the entries as the children of dir
    for _, entry := range entries {
      // Check to make sure the file is regular or a directory
      // Skip if not one of those
      isDir := entry.IsDir()
      if !entry.Mode().IsRegular() && !isDir {
        continue
      }
      // Create the DirEntry
      de := &DirEntry{
        name: entry.Name(),
        parent: dir,
        isDir: isDir,
        lastMod: entry.ModTime().Unix(),
      }
      // Run readDir() on entry if it's a directory
      if isDir {
        if err := buildDir(path.Join(dirPath, de.name), de); err != nil {
          return err
        }
      }
      // Add de to the dir's children
      dir.children = append(dir.children, de)
    }
    return nil
  }
  // Get file info for the root
  info, err := os.Stat(rootPath)
  if err != nil {
    return nil, err
  } else if !info.IsDir() {
    return nil, errors.New("root is not a directory")
  }
  // Create the root and build the file tree
  root := &DirEntry{
    name: info.Name(),
    parent: nil,
    isDir: true,
    lastMod: info.ModTime().Unix(),
  }
  if err := buildDir(rootPath, root); err != nil {
    return nil, err
  }
  ftree := &FileTree{
    root: root,
    rootPath: rootPath,
    doneChan: make(chan struct{}),
  }
  return ftree, nil
}

func (ft *FileTree) watch() {
  for {
    select {
      case <-doneChan:
        return
      default:
    }
  }
}

func (ft *FileTree) Remove() {
  doneChan <- struct{}
}

func walk(v string, walkFunc func() {
  
}
