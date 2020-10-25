int inputAndValidation(char *inputName){//parameters is for the display name of the input
    int inputNumber;
    char ch;//variable to check if there are characters existed in the input
    printf("%s: ",inputName);
    while(((scanf("%d%c", &inputNumber, &ch)!=2 || ch!='\n') && clean_stdin())){
        printf("[Please Enter a Valid Input]\n");
        printf("%s: ",inputName);
    }
    return inputNumber;

}
int clean_stdin(){
    while (getchar()!='\n');
    return 1;
}
