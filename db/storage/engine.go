package storage

//#include "tree.h"
import (
	"C"
)

// Engine is the storage engine
type Engine struct {
	collectionTrees map[string]C.Tree // [Collection Name]Tree
}

// NewEngine returns a new Engine instance or an error
func NewEngine() (*Engine, error) {
	return &Engine{
		collectionTrees: make(map[string]C.Tree),
	}, nil
}

func newTree(data interface{}) C.Tree {
	tree := C.newTree()
	C.insert(tree, &data)
	return tree
}
