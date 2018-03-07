package parse

const (
	WaitForLength = 0
	WaitForData = 1
)

type Parse struct
{
	curData []byte
	curDataLength int
	curStatus int
	needDataLength int
}


func (p Parse) parse(data []byte, num int) {
	if (p.curStatus == WaitForLength){
		if (num >= 4){
			p.needDataLength = 1
			p.curStatus = WaitForData
		}
	}else{
		if (p.curDataLength + num >= p.needDataLength){
			
		}
	}
}




