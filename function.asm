
%macro debug 1 ;address of variable ; debug msg
	mov rdi,%1
	mov al,0
	call printf
%endmacro

%macro read 3 ;In_format, address of variable and prompt
	mov rdi,%3
	mov al,0
	call printf	

	mov rsi,%2
	mov rdi,%1
	mov rax,0
	call scanf
%endmacro

%macro write 2;Out_format and address of variable
	mov rsi,[%2]
	mov rdi,%1
	mov rax,0
	call printf
%endmacro

%macro readrecord 5;In_format, address of variable, field_num, temporary and prompt
	push RAX 
	mov rdi,%5
	mov al,0
	call printf

	mov rsi,%4
	mov rdi,%1
	mov rax,0
	call scanf

	mov eax,%3
	sub eax,1
	mov edx,0
	mov ebx,4
	imul ebx

	add eax,%2
	mov ebx,[%4]
	mov DWORD [eax],ebx
	pop RAX
%endmacro	

%macro writerecord 7 ; writerecords t1,fmt_out,t9,t8,4,count1,count2
	mov ebx,0
	mov DWORD [%4],%5
Z%6:	mov eax,[%1+ebx]
	mov [%3],eax
	;write %2,%3
	mov rsi,[%3]
	mov rdi,%2
	mov rax,0
	call printf

	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%4]
	sub ecx,1
	mov DWORD [%4],ecx
	cmp ecx,0
	jne Z%6
Z%7:
%endmacro

%macro addrecordstwo 7; addrecords st1,s1,t1,t10,4,num1,num2
	mov ebx,0 ;offset
	mov DWORD [%4],%5
.W%6:	mov eax,[%2+ebx]
	mov edx,[%3+ebx]
	add eax,edx
	;mov DWORD [%6],eax
	;write fmt_out2,%6
	mov DWORD [%1+ebx],eax
	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%4]
	sub ecx,1
	mov DWORD [%4],ecx
	cmp ecx,0
	jne .W%6
.W%7:	
%endmacro

%macro addrr 5;t1,rec1,(field-1)*4,rec2,(field-1)*4
	;mov eax,[%4]
	mov ebx,%3
	mov DWORD eax,[%2+ebx]	
	mov ebx,%5
	mov DWORD ecx,[%4+ebx]
	add eax,ecx
	mov DWORD [%1],eax
%endmacro

%macro addri 4;t1,rec1,(field-1)*4,t2
	mov eax,[%4]
	mov ebx,%3
	mov DWORD ecx,[%2+ebx]
	add eax,ecx
	mov DWORD [%1],eax
%endmacro

%macro addrn 4;t1,rec1,(field-1)*4,num
	mov eax,%4
	mov ebx,%3
	mov DWORD ecx,[%2+ebx]
	add eax,ecx
	mov DWORD [%1],eax
%endmacro

%macro subrr 5;t1,rec1,(field-1)*4,rec2,(field-1)*4
	;mov eax,[%4]
	mov ebx,%3
	mov DWORD eax,[%2+ebx]	
	mov ebx,%5
	mov DWORD ecx,[%4+ebx]
	sub eax,ecx
	mov DWORD [%1],eax
%endmacro

%macro subri 4;t1,rec1,(field-1)*4,t2
	mov ebx,[%4]
	mov ecx,%3
	mov DWORD eax,[%2+ecx]
	sub eax,ecx
	mov DWORD [%1],eax
%endmacro

%macro subrn 4;t1,rec1,(field-1)*4,num
	mov ebx,%4
	mov ecx,%3
	mov DWORD eax,[%2+ecx]
	sub eax,ecx
	mov DWORD [%1],eax
%endmacro

%macro mulrecordstwo 7; addrecords st1,s1,t1,t10,4,num1,num2
	mov ebx,0 ;offset
	mov esi,[%3]
	mov DWORD [%4],%5
.W%6:	mov eax,[%2+ebx]
	mov edx,0
	imul esi
	;mov DWORD [%6],eax
	;write fmt_out2,%6
	mov DWORD [%1+ebx],eax
	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%4]
	sub ecx,1
	mov DWORD [%4],ecx
	cmp ecx,0
	jne .W%6
.W%7:	
%endmacro

%macro mulrecordsone 7; addrecords st1,s1,num,t10,4
	mov ebx,0 ;offset
	mov esi,%3
	mov DWORD [%4],%5
.W%6:	mov eax,[%2+ebx]
	mov edx,0
	imul esi
	;mov DWORD [%6],eax
	;write fmt_out2,%6
	mov DWORD [%1+ebx],eax
	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%4]
	sub ecx,1
	mov DWORD [%4],ecx
	cmp ecx,0
	jne .W%6
.W%7:	
%endmacro

%macro divrecordstwo 7; addrecords st1,s1,t1,t10,4
	mov ebx,0 ;offset
	mov esi,[%3]
	mov DWORD [%4],%5
.W%6:	mov eax,[%2+ebx]
	mov edx,0
	idiv esi
	;mov DWORD [%6],eax
	;write fmt_out2,%6
	mov DWORD [%1+ebx],eax
	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%4]
	sub ecx,1
	mov DWORD [%4],ecx
	cmp ecx,0
	jne .W%6
.W%7:	
%endmacro

%macro divrecordsone 7; addrecords st1,s1,t1,t10,4
	mov ebx,0 ;offset
	mov esi,%3
	mov DWORD [%4],%5
.W%6:	mov eax,[%2+ebx]
	mov edx,0
	idiv esi
	;mov DWORD [%6],eax
	;write fmt_out2,%6
	mov DWORD [%1+ebx],eax
	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%4]
	sub ecx,1
	mov DWORD [%4],ecx
	cmp ecx,0
	jne .W%6
.W%7:	
%endmacro

%macro mulrr 5;t1,rec1,(field-1)*4,rec2,(field-1)*4
	;mov eax,[%4]
	mov ebx,%3
	mov DWORD eax,[%2+ebx]	
	mov ebx,%5
	mov DWORD ecx,[%4+ebx]
	mov edx,0	
	imul ecx
	mov DWORD [%1],eax
%endmacro

%macro mulri 4;t1,rec1,(field-1)*4,t2
	mov eax,[%4]
	mov ebx,%3
	mov DWORD ecx,[%2+ebx]
	imul ecx
	mov DWORD [%1],eax
%endmacro

%macro mulrn 4;t1,rec1,(field-1)*4,t2
	mov eax,%4
	mov ebx,%3
	mov DWORD ecx,[%2+ebx]
	imul ecx
	mov DWORD [%1],eax
%endmacro

%macro divrr 5;t1,rec1,(field-1)*4,rec2,(field-1)*4	
	mov edx,%5
	mov ebx,[%4+edx]
	mov ecx,%3
	mov DWORD eax,[%2+ecx]
	mov edx,0
	idiv ebx
	mov DWORD [%1],eax
%endmacro

%macro divri 4;t1,rec1,(field-1)*4,t2
	mov ebx,[%4]
	mov ecx,%3
	mov DWORD eax,[%2+ecx]
	mov edx,0
	idiv ebx
	mov DWORD [%1],eax
%endmacro

%macro divrn 4;t1,rec1,(field-1)*4,t2
	mov ebx,%4
	mov ecx,%3
	mov DWORD eax,[%2+ecx]
	mov edx,0
	idiv ebx
	mov DWORD [%1],eax
%endmacro

%macro assignrecords 6; assignrecords s1,t1,t10,4,num1,num2
	mov ebx,0 ;offset
	mov DWORD [%3],%4
.W%5:	mov eax,[%2+ebx]
	mov DWORD [%1+ebx],eax
	add ebx,4
	mov ecx,0
	mov DWORD ecx,[%3]
	sub ecx,1
	mov DWORD [%3],ecx
	cmp ecx,0
	jne .W%5
.W%6:	
%endmacro

%macro store 2 ;store c2,20 stores value 20 into variable c2
	mov ebx,%2
	mov [%1],ebx
%endmacro

%macro storerecord 3;rec1,(field-1)*4,num
	mov ebx,%2
	mov eax,%3
	mov DWORD [%1+ebx],eax
%endmacro

%macro assignrecord 3;rec1,(field-1)*4,t1
	mov eax,[%3]
	mov ebx,%2
	mov DWORD [%1+ebx],eax
%endmacro

%macro assignfield 3;t1,rec1,(field-1)*4
	mov ebx,%3
	mov eax,[%2+ebx]
	mov DWORD [%1],eax
%endmacro

%macro assignfields 3;rec1,(field-1)*4,rec2,(field-1)*4
	mov ebx,%4
	mov eax,[%3+ebx]
	mov ebx,%2
	mov DWORD [%1+ebx],eax
%endmacro


%macro multwo 3; multwo t1,c2,d2 t1=c2*d2
	mov eax,[%3]
	mov edx,0
	mov ebx,[%2]
	imul ebx; eax=eax*ebx;
	mov [%1],eax
%endmacro

%macro addtwo 3; addtwo t1,c2,d2 t1=c2+d2
	mov eax,[%3]
	mov ebx,[%2]
	add eax,ebx
	mov [%1],eax
%endmacro

%macro subtwo 3; subtwo t1,c2,d2 t1=c2-d2
	mov eax,[%2]
	mov ebx,[%3]
	sub eax,ebx dest=dest-src
	mov [%1],eax
%endmacro

%macro divtwo 3; divtwo t1,c2,d2 t1=c2/d2
	mov eax,[%2]
	mov edx,0
	mov ebx,[%3]
	idiv ebx
	mov [%1],eax
%endmacro

%macro assigntwo 2; assigntwo t1,t2 t1<---t2
	mov ebx,[%2]
	mov [%1],ebx
%endmacro

%macro addone 3; addone t1,c2,num t1=c2+num
	mov ebx,%3
	mov eax,[%2]
	add eax,ebx
	mov [%1],eax
%endmacro
	
%macro mulone 3
	mov ebx,%3
	mov eax,[%2]
	mov edx,0
	imul ebx
	mov [%1],eax
%endmacro

%macro subone 3; addone t1,c2,num t1=c2-num
	mov ebx,%3
	mov eax,[%2]
	sub eax,ebx
	mov [%1],eax
%endmacro
	
%macro divone 3
	mov ebx,%3
	mov eax,[%2]
	mov edx,0
	idiv ebx
	mov [%1],eax
%endmacro

%macro addzero 3; addone t1,num,num t1=num+num
	mov ebx,%3
	mov eax,%2
	add eax,ebx
	mov [%1],eax
%endmacro
	
%macro mulzero 3
	mov ebx,%3
	mov eax,%2
	mov edx,0
	imul ebx
	mov [%1],eax
%endmacro

%macro subzero 3; addone t1,c2,num t1=c2-num
	mov ebx,%3
	mov eax,%2
	sub eax,ebx
	mov [%1],eax
%endmacro
	
%macro divzero 3
	mov ebx,%3
	mov eax,%2
	mov edx,0
	idiv ebx
	mov [%1],eax
%endmacro

%macro comparetwo 2;
	mov eax,[%1]
	mov ebx,[%2]
	cmp eax,ebx
%endmacro

%macro andtwo 3
	mov ebx,[%3]
	mov eax,[%2]
	and eax,ebx
	mov [%1],eax 
%endmacro

%macro andone 3
	mov ebx,%3
	mov eax,[%2]
	and eax,ebx
	mov [%1],eax 
%endmacro

%macro ortwo 3
	mov ebx,[%3]
	mov eax,[%2]
	or eax,ebx
	mov [%1],eax 
%endmacro

%macro orone 3
	mov ebx,%3
	mov eax,[%2]
	or eax,ebx
	mov [%1],eax 
%endmacro

%macro nottwo 2
	mov eax,[%2]
	xor eax,1
	mov [%1],eax 
%endmacro

%macro notone 2
	mov eax,%2
	xor eax,1
	mov [%1],eax
%endmacro

%macro lessthanequalone 3
	mov ebx,%3
	mov eax,[%2]
	cmp eax,ebx
	jle .X1
	mov eax,0
	mov [%1],eax
	jmp .X2
.X1:	mov eax,1
	mov [%1],eax
.X2:
%endmacro

%macro lessthanone 3
	mov ebx,%3
	mov eax,[%2]
	cmp eax,ebx
	jl .X3
	mov eax,0
	mov [%1],eax
	jmp .X4
.X3:	mov eax,1
	mov [%1],eax
.X4:
%endmacro

%macro greatthanequalone 3
	mov ebx,%3
	mov eax,[%2]
	cmp eax,ebx
	jge .X5
	mov eax,0
	mov [%1],eax
	jmp .X6
.X5:	mov eax,1
	mov [%1],eax
.X6:
%endmacro

%macro greatthanone 3
	mov ebx,%3
	mov eax,[%2]
	cmp eax,ebx
	jg .X7
	mov eax,0
	mov [%1],eax
	jmp .X8
.X7:	mov eax,1
	mov [%1],eax
.X8:
%endmacro

%macro lessthanequaltwo 3
	mov ebx,[%3]
	mov eax,[%2]
	cmp eax,ebx
	jle .X9
	mov eax,0
	mov [%1],eax
	jmp .X10
.X9:	mov eax,1
	mov [%1],eax
.X10:
%endmacro

%macro lessthantwo 3
	mov ebx,[%3]
	mov eax,[%2]
	cmp eax,ebx
	jl .X11
	mov eax,0
	mov [%1],eax
	jmp .X12
.X11:	mov eax,1
	mov [%1],eax
.X12:
%endmacro

%macro greatthanequaltwo 3
	mov ebx,[%3]
	mov eax,[%2]
	cmp eax,ebx
	jge .X13
	mov eax,0
	mov [%1],eax
	jmp .X14
.X13:	mov eax,1
	mov [%1],eax
.X14:
%endmacro

%macro greatthantwo 3
	mov ebx,[%3]
	mov eax,[%2]
	cmp eax,ebx
	jg .X15
	mov eax,0
	mov [%1],eax
	jmp .X16
.X15:	mov eax,1
	mov [%1],eax
.X16:
%endmacro

%macro equaltwo 3
	mov ebx,[%3]
	mov eax,[%2]
	cmp eax,ebx
	je .X17
	mov eax,0
	mov [%1],eax
	jmp .X18
.X17:	mov eax,1
	mov [%1],eax
.X18:
%endmacro

%macro equalone 3
	mov ebx,%3
	mov eax,[%2]
	cmp eax,ebx
	je .X19
	mov eax,0
	mov [%1],eax
	jmp .X20
.X19:	mov eax,1
	mov [%1],eax
.X20:
%endmacro

%macro notequaltwo 3
	mov ebx,[%3]
	mov eax,[%2]
	cmp eax,ebx
	jne .X21
	mov eax,0
	mov [%1],eax
	jmp .X22
.X21:	mov eax,1
	mov [%1],eax
.X22:
%endmacro

%macro notequalone 3
	mov ebx,%3
	mov eax,[%2]
	cmp eax,ebx
	jne .X23
	mov eax,0
	mov [%1],eax
	jmp .X24
.X23:	mov eax,1
	mov [%1],eax
.X24:
%endmacro

