#i n cl u d e <B r i d g e . h>
#i n cl u d e <Y u n S e rv e r . h>
#i n cl u d e <Y u nC l i e n t . h>

Y u n S e rv e r s e r v e r ;
void s e t u p ( ) {
// B r i d g e s t a r t u p
pinMode ( 1 3 , OUTPUT) ;
pinMode ( 1 2 , OUTPUT) ; // S a l i d a de
pinMode ( 1 1 , INPUT ) ; // I l u m i n a c i o n I
pinMode ( 1 0 , OUTPUT) ; // S a l i d a de
pinMode ( 9 , INPUT ) ; // I l u m i n a c i o n I I
pinMode ( 8 , OUTPUT) ; // S a l i d a de
pinMode ( 6 , INPUT ) ; // I l u m i n a c i o n I I I
d i g i t a l W r i t e ( 1 3 , LOW) ;
B r i d g e . b e g i n ( ) ;
d i g i t a l W r i t e ( 1 3 , HIGH ) ;
s e r v e r . l i s t e n O n L o c a l h o s t ( ) ;
s e r v e r . b e g i n ( ) ;
}

void l o o p ( ) {
Y u nC l i e n t c l i e n t = s e r v e r . a c c e p t ( ) ;
i f ( c l i e n t ) {
p r o c e s s ( c l i e n t ) ;
c l i e n t . s t o p ( ) ;
}
d e l a y ( 5 0 ) ;
}

void p r o c e s s ( Y u nC l i e n t c l i e n t ) {
S t r i n g command = c l i e n t . r e a d S t r i n g U n t i l ( ’ / ’ ) ;
i f ( command == " d i g i t a l " ) {
di gi talC omma n d ( c l i e n t ) ;
}
i f ( command == " a n a l o g " ) {
analogCommand ( c l i e n t ) ;
}
i f ( command == "mode " ) {
modeCommand ( c l i e n t ) ;
}
}


void di gi talC omma n d ( Y u nC l i e n t c l i e n t ) {
i n t pi n , v a l u e ;

p i n = c l i e n t . p a r s e I n t ( ) ;
i f ( c l i e n t . r e a d ( ) == ’ / ’ ) {
v a l u e = c l i e n t . p a r s e I n t ( ) ;
d i g i t a l W r i t e ( pi n , v a l u e ) ;
}
e l s e {
v a l u e = d i g i t a l R e a d ( p i n ) ;
}

c l i e n t . p r i n t ( F ( " Pin ␣D" ) ) ;
c l i e n t . p r i n t ( p i n ) ;
c l i e n t . p r i n t ( F ( " ␣ s e t ␣ t o ␣ " ) ) ;
c l i e n t . p r i n t l n ( v a l u e ) ;
S t r i n g key = "D" ;
key += p i n ;
B r i d g e . pu t ( key , S t r i n g ( v a l u e ) ) ;
}

void analogCommand ( Y u nC l i e n t c l i e n t ) {
i n t pi n , v a l u e ;
p i n = c l i e n t . p a r s e I n t ( ) ;
i f ( c l i e n t . r e a d ( ) == ’ / ’ ) {
v a l u e = c l i e n t . p a r s e I n t ( ) ;
a n a l o gW r i t e ( pi n , v a l u e ) ;
// Send f e e d b a c k t o c l i e n t
c l i e n t . p r i n t ( F ( " Pin ␣D" ) ) ;
c l i e n t . p r i n t ( p i n ) ;
c l i e n t . p r i n t ( F ( " ␣ s e t ␣ t o ␣ a n a l o g ␣ " ) ) ;
c l i e n t . p r i n t l n ( v a l u e ) ;
S t r i n g key = "D" ;
key += p i n ;
B r i d g e . pu t ( key , S t r i n g ( v a l u e ) ) ;
}
e l s e {
v a l u e = a nal o gRea d ( p i n ) ;
c l i e n t . p r i n t ( F ( " Pin ␣A" ) ) ;
c l i e n t . p r i n t ( p i n ) ;
c l i e n t . p r i n t ( F ( " ␣ r e a d s ␣ a n a l o g ␣ " ) ) ;
c l i e n t . p r i n t l n ( v a l u e ) ;
S t r i n g key = "A" ;
key += p i n ;

B r i d g e . pu t ( key , S t r i n g ( v a l u e ) ) ;
}
}

void modeCommand ( Y u nC l i e n t c l i e n t ) {
i n t p i n ;
p i n = c l i e n t . p a r s e I n t ( ) ;
i f ( c l i e n t . r e a d ( ) != ’ / ’ ) {
c l i e n t . p r i n t l n ( F ( " e r r o r " ) ) ;
r e t u r n ;
}

S t r i n g mode = c l i e n t . r e a d S t r i n g U n t i l ( ’ \ r ’ ) ;
i f ( mode == " i n p u t " ) {
pinMode ( pi n , INPUT ) ;
// Send f e e d b a c k t o c l i e n t
c l i e n t . p r i n t ( F ( " Pin ␣D" ) ) ;
c l i e n t . p r i n t ( p i n ) ;
c l i e n t . p r i n t ( F ( " ␣ c o n f i g u r e d ␣ a s ␣INPUT ! " ) ) ;
r e t u r n ;
}
i f ( mode == " o u t p u t " ) {
pinMode ( pi n , OUTPUT) ;
// Send f e e d b a c k t o c l i e n t
c l i e n t . p r i n t ( F ( " Pin ␣D" ) ) ;
c l i e n t . p r i n t ( p i n ) ;
c l i e n t . p r i n t ( F ( " ␣ c o n f i g u r e d ␣ a s ␣OUTPUT! " ) ) ;
r e t u r n ;
}
c l i e n t . p r i n t ( F ( " e r r o r : ␣ i n v a l i d ␣mode␣ " ) ) ;
c l i e n t . p r i n t ( mode ) ;
}
