package storage

import (
	"time"

	"github.com/google/btree"
)

// Record is a log record in the DB
type Record struct {
	btree.Item
	Data       interface{}
	InsertedAt time.Time
}

func NewRecord(data interface{}) Record {
	return Record{
		Data:       data,
		InsertedAt: time.Now(),
	}
}

// Less satisfies the btree.Item's Less abstract function
func (r Record) Less(other Record) bool {
	return r.InsertedAt.Before(other)
}
