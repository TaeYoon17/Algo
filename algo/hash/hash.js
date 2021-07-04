
const HashBucket=class{
    constructor(key,value){
        this.key=key;
        this.value=value;
        this.status="EMPTY";
    }
}
const OpenAddressing=class{
    constructor(size){
        this.bucketSize=size;
        this.currentCount=0;
        this.bucket=new Array(size);
    }
    addData(newBucket){
        let bucketIndex=this.hashFunction(newBucket.key);
        if(bucketIndex<0||bucketIndex>=this.bucketSize||isNaN(bucketIndex)){
            throw "잘못된 해시 테이블 주소가 계산되었음";
        }
        let tempIndex=bucketIndex;
        do{
            const bucket=this.bucket[tempIndex];
            
            if(this.isEmptyOrDeletedBucket(bucket)===1){
                this.bucket[tempIndex]=newBucket;
                this.bucket[tempIndex].status="USED";
                this.currentCount++;
                break;
            }else{
                if(newBucket.key===bucket.key){
                    console.log("중복된 키 입니다.");
                    break;
                }else{
                    tempIndex=(tempIndex+1)%this.bucketSize;
                    if(tempIndex===bucketIndex){
                        console.log("해시 테이블이 가득 참");
                        break;
                    }
                }
            }
        }while(tempIndex!==bucketIndex);
    }
    removeData(key){
        const bucket=this.search(key);
        if(bucket===undefined){
            console.log("검색키가 존재하지 않음");
        }else{
            bucket.status="DELETED";
            bucket.key="";
            bucket.value=0;
            this.currentCount--;
        }
    }
    search(key){
        const bucketIndex=this.hashFunction(key);
        if(bucketIndex<0) throw "잘못된 해시 테이블 계산";
        let tempIndex=bucketIndex;
        do{
            const bucket=this.bucket[tempIndex];
            if(this.isEmptyBucket(bucket)===1){
                console.log("검색키가 존재하지 않음");
                return undefined;
            }else{
                if(bucket.status==="USED"&&key===bucket.key){
                    return bucket;
                }else{
                    tempIndex=(tempIndex+1)%this.bucketSize;
                    if(tempIndex===bucketIndex){
                        console.log("검색키가 존재하지 않음");
                        return undefined;
                    }
                }
            }
        }while(tempIndex!==bucktIndex)
    }
    displayHash(){
        for(let v of this.bucket){
            if(v!==undefined) console.log(v.key, v.value, v.status);
        }
    }
    getCount(){}
    deleteHashTable(){
        this.bucketSize=0;
        this.currentCount=0;
        this.bucket=[];
    }

    hashFunction(key){
        let ret=0;
        const temp_key=this.stringToInt(key);
        if(this.bucketSize>0){
            ret=temp_key%this.bucketSize;
        }
        return ret;
    }
    stringToInt(key){
        let num=0;
        for(let v of key){
            num=(num*31)+v.charCodeAt(0);
        }
        return num;
    }
    isEmptyBucket(){}
    isEmptyOrDeletedBucket(bucket){
        if(bucket===undefined) return 1;
        if(bucket.status==="USED") return 0;
        else return 1;
    }
}
const bucket=[new HashBucket("january",1),
    new HashBucket("february",2),
    new HashBucket("march",3),
    new HashBucket("april",4),
    new HashBucket("may",5),
    new HashBucket("june",6),
    new HashBucket("july",7),
    new HashBucket("august",8),
    new HashBucket("septemver",9),
    new HashBucket("october",10),
    new HashBucket("november",11),
    new HashBucket("december",12)]
const OpenAdd=(bucket,HashTable)=>{
    for(let i=0; i<12; i++){
        HashTable.addData(bucket[i]);
    }
}
const HashTable=new OpenAddressing(13);
//OpenAdd(bucket,HashTable);

export {bucket,OpenAdd};