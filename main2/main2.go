package main

import (
	"fmt"
	"io/ioutil"
	"sync"
)

var (
	ignore = map[string]bool{
		".DS_Store": true,
		"node_modules": true,
		"__pycache__": true,
		"Machine Learning A-Z Template Folder": true,
		"HandOnML": true,
		"MLProject": true,
	}
)

func read(node *TreeNode) {
	contents, err := ioutil.ReadDir(node.FullPath())
	if err != nil {
		panic(err)
	}
	for _, info := range contents {
		n := &TreeNode{
			name: info.Name(),
			dir: info.IsDir(),
			mod: info.ModTime().Unix(),
			parent: node,
		}
		node.AppendChild(n)
		if n.dir {
			read(n)
		}
	}
}

func main() {
	root := &TreeNode{
		name: "..",
		dir: true,
		mod: 0,
	}
	read(root)
	done := make(chan int, 1)
	root.Walk(done)
	<-done
}

type TreeNode struct {
	name string
	dir bool
	mod int64
	parent *TreeNode
	children map[string]*TreeNode
	sync.RWMutex
}

func(node *TreeNode) AppendChild(n *TreeNode) error {
	if node.dir {
		node.children[n.name] = n
		return nil
	}
	return fmt.Errorf("tree node is a file")
}

// func(node *TreeNode)

func(node *TreeNode) Walk(doneChan chan int) {
	node.RLock()
	defer node.RUnlock()
	n := 0
	walkChan := make(chan int, 10)
	for _, child := range node.children {
		fmt.Printf("%+v\t%s\n", child, child.FullPath())
		if ignore[child.name] {
			continue
		} else if child.dir {
			child.Walk(walkChan)
			n++
		}
	}
	// for i := 0; i < n; i++ {
	// 	<-walkChan
	// }
	doneChan <- 1
}

func(node *TreeNode) FullPath() string {
	if node.parent == nil {
		return node.name
	}
	return node.parent.FullPath() + "/" + node.name
}

func(node *TreeNode) GetRoot() *TreeNode {
	if node.parent == nil {
		return node
	}
	return node.GetRoot()
}
