const arr=[80,75,10,60,15,49,12,25];

const selection=(value)=>{
    for(let i=0; i<value.length-1; i++){
        let min=i;
        for(let j=i+1; j<value.length;j++){
            if(value[j]<value[min]){
                min=j;
            }
        }
        let temp=value[i];
        value[i]=value[min];
        value[min]=temp;
        console.log(value);
    }
    return value;
}
const partitionQuickSort=(value,start,end)=>{
    let pivot=end;
    let right=end;
    let left=start;
    while(left<right){
        while((value[left]<value[pivot])&&(left<right)) left++;
        while((value[end]>=value[pivot])&&(left<right)) right--;
        if(left<right){
            let temp=value[left];
            value[left]=value[right];
            value[right]=temp;
        }
    }
    temp=value[pivot];
    value[pivot]=value[right];
    value[right]=temp;
    console.log(value);
    return {right,value};
}
const quickSort=(value=[],start=0,end)=>{
    let pivot=0;
    if(start<end){
        let {right,value}=partitionQuickSort(value,start,end);
        let pivot=right;
        quickSort(value,start,pivot-1);
        quickSort(value,pivot+1,end);
    }
}
quickSort(arr,0,arr.length-1);
console.log(arr);
