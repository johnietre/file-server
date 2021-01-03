package main

import (
	"io/ioutil"
)

var (
	ignore = map[string]bool{
		".DS_Store":                            true,
		"node_modules":                         true,
		"__pycache__":                          true,
		"Machine Learning A-Z Template Folder": true,
		"HandOnML":                             true,
		"MLProject":                            true,
		".ipynb_checkpoints":			true,
	}
)

func main() {
	root := &TreeNode{
		name:     ".",
		dir:      true,
		mod:      0,
		children: new(DLLNode),
	}
	read(root)
	done := make(chan int, 1)
	root.Walk(done)
	<-done
}

func read(node *TreeNode) {
	contents, err := ioutil.ReadDir(node.FullPath())
	if err != nil {
		panic(err)
	}
	for _, info := range contents {
		n := &TreeNode{
			name:   info.Name(),
			dir:    info.IsDir(),
			mod:    info.ModTime().Unix(),
			parent: node,
		}
		node.AppendChild(n)
		if n.dir {
			n.children = new(DLLNode)
			read(n)
		}
	}
}
