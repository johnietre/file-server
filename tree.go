package main

import (
	"fmt"
	"sync"
)

// TreeNode is used to the tree for representing the folder structure
type TreeNode struct {
	name string
	dir bool
	mod int64
	parent *TreeNode
	children *DLLNode
	sync.RWMutex
}

// AppendChild appends a *TreeNode to the children list
func(node *TreeNode) AppendChild(n *TreeNode) error {
	if node.dir {
		node.children.Append(n)
		return nil
	}
	return fmt.Errorf("tree node is a file")
}

// Walk concurrently walks through the tree
func(node *TreeNode) Walk(doneChan chan int) {
	node.RLock()
	defer node.RUnlock()
	n := 0
	walkChan := make(chan int, 10)
	for _, child := range node.children.ToArray() {
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

// Find returns the tree node with the given path
func(node *TreeNode) Find(path string) *TreeNode {
	p := node.name + "/"
	if path == "/" || p == "/" {
		return nil
	}
	return node
}

// FullPath returns the full path of the node
func(node *TreeNode) FullPath() string {
	if node.parent == nil {
		return node.name
	}
	return node.parent.FullPath() + "/" + node.name
}

// GetRoot returns the root of tree
func(node *TreeNode) GetRoot() *TreeNode {
	if node.parent == nil {
		return node
	}
	return node.GetRoot()
}
