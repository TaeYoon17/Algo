
const Slot=class{
    constructor(key,value){
        this.key=key;
        this.value=value;
    }
}
const LinkedListNode=class{
    constructor(slot){
        this.slot=slot;
        this.next=null;
    }
    displaySlot(){
        console.log(`key: ${this.slot.key} value: ${this.slot.value}`);
    }
    getSlot(){
        return this.slot;
    }
}
const LinkedList=class{
    constructor(){
        this.currentCount=0;
        this.headerNode=null;
    }
    appendNode(slot){
        const newNode=new LinkedListNode(slot);
        if(this.headerNode===null) this.headerNode=newNode;
        else{
            let tempNode=this.headerNode;
                for(let i=0; i<this.currentCount-1; i++) {
                    tempNode=tempNode.next;
            }
            tempNode.next=newNode;
        }
        this.currentCount++;
    }
    removeNode(index){
        let tempNode=this.headerNode.next;
        let beforeNode=this.headerNode;
        for(let i=0; i<this.currentCount; i++){
            if(i===index-1){
                beforeNode.next=tempNode.next;
                break;
            }
            beforeNode=tempNode;
            tempNode=tempNode.next;
        }
        this.currentCount--;
    }
    searchNode(key){
        let tempNode=this.headerNode;
        for(let i=0; i<this.currentCount; i++){
            if(tempNode.slot.key===key) return [tempNode,i];
            tempNode=tempNode.next;
        }
        console.log("해당 키는 없습니다.");
        return [null,null]
    }
    displayNode(){
        let tempNode=this.headerNode;
        for(let i=0; i<this.currentCount; i++){
            tempNode.displaySlot();
            tempNode=tempNode.next;
        }
    }
}
const Chaining=class{
    constructor(size){
        this.currentSize=0;
        this.bucketSize=size;
        this.HashBucket=new Array(size);
    }

    addData(slot){
        const bucketIndex=this.hashFunction(slot.key);
        if(bucketIndex<0||bucketIndex>this.bucketSize){
            throw "잘못된 인덱스";
        }
        const bucket=this.HashBucket[bucketIndex];
        if(bucket===undefined) this.HashBucket[bucketIndex]=new LinkedList();
        this.HashBucket[bucketIndex].appendNode(slot);
        this.currentSize++;
    }
    removeData(key){
        const bucketIndex=this.hashFunction(key);
        if(bucketIndex<0||bucketIndex>this.bucketSize){
            throw "잘못된 인덱스";
        }
        const [Node,index]=this.HashBucket[bucketIndex].searchNode(key);
        this.HashBucket[bucketIndex].removeNode(index);
        this.currentSize--;
    }
    search(key){
        const bucketIndex=this.hashFunction(key);
        const [Node,index]=this.HashBucket[bucketIndex].searchNode(key);
        if(Node===null&&index===null) return new Slot(null,null);
        else return Node.getSlot();
    }
    displayHash(){
        console.log(`HashTable CurrentSize ${this.currentSize}`);
        this.HashBucket.forEach((v,i)=>{
            console.log(`HashBucket[${i}]`);
            if(v!==undefined) v.displayNode();
            else console.log("undefined");
        })
    }
    searchSlot(key){
        const bucket=this.searchBucket(key);
        const [Node,index]=bucket.searchNode(key);
        return [Node.slot,index];
    }
    hashFunction(key){
        if(!this.bucketSize>0){
            throw "이상한 bucketSize";
        }else return this.stringToInt(key)%this.bucketSize;
    }
    stringToInt(key){
        let num=0;
        for(let v of key){
            num=(num*31)+v.charCodeAt(0);
        }
        return num;
    }
}

const Slots=[
    new Slot("january",1),
    new Slot("february",2),
    new Slot("march",3),
    new Slot("april",4),
    new Slot("may",5),
    new Slot("june",6),
    new Slot("july",7),
    new Slot("august",8),
    new Slot("septemver",9),
    new Slot("october",10),
    new Slot("november",11),
    new Slot("december",12)
]
const OpenAdd=(bucket,HashTable)=>{
    for(let i=0; i<12; i++){
        HashTable.addData(bucket[i]);
    }
}
const HashTable=new Chaining(13);
OpenAdd(Slots,HashTable);
HashTable.removeData("april");
console.log(HashTable);
const slot=HashTable.search("april");
console.log(slot.key,slot.value);