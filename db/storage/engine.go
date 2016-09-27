package storage

import (
	"github.com/google/btree"
)

// Engine is the storage engine
type Engine struct {
	collectionTrees map[string]C.Tree // [Collection Name]Tree
}

// NewEngine returns a new Engine instance or an error
func NewEngine() (*Engine, error) {
	return &Engine{
		collectionTrees: make(map[string]*btree.Btree),
	}, nil
}

func (e *Engine) newTree(collection string, data interface{}) {
	e.collectionTrees[collection] = btree.New(2)
	if data != nil {
		rec := NewRecord(data)
		e.collectionTrees[collection].ReplaceOrInsert(rec)
	}
}
