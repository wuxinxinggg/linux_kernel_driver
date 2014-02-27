#!/bin/bash
# tree2dot.sh --- transfer a "tree"(such as the result of tree,calltree)
#                 to a p_w_picpath discribed by DOT language(provided by Graphviz)
# author: falcon<zhangjinw@gmail.com>
# update: 2007-11-14
# usage: 
#       tree -L 2 -d /path/to/a/directory | bash tree2dot.sh > tree.dot
#       cd /path/to/a/c/project/; calltree -gb -np -m *.c | bash tree2dot.sh > tree.dot

# indicate the symbols you not concern with space as decollator here
filterstr="";

# transfer the tree result to a file described in DOT language
grep -v ^$ | grep -v "^[0-9]* director" \
| awk '{if(NR==1) system("basename "$0); else printf("%s\n", $0);}' |\
awk -v fstr="$filterstr" '# function for filter the symbols you not concern
        function need_filter(node) {
                for( i in farr ) { 
                if(match(node,farr[i]" ") == 1 || match(node,"^"farr[i]"$") == 1) {
                        return 1;
                }
                }
                return 0;
        }
        BEGIN{ # filternode array are used to record the symbols who have been filtered.
                oldnodedepth=-1; oldnode=""; nodep[-1]=""; filternode[nodep[-1]]=0;
                # store the symbols to an array farr
                split(fstr,farr," ");
                # print some setting info
                printf("digraph G{\n"); 
                printf("\trankdir=LR;\n");
                printf("\tsize=\"800,600\";\n");
                printf("\tnode [fontsize=10,fontcolor=red,style=filled,fillcolor=lightblue];\n");
        }{
                # get the node, and its depth(nodedepth)
                nodedepth=match($0, "[^| `]");
                node=substr($0,nodedepth); 
                nodedepth=int(nodedepth/4)
                # if whose depth is 1 less than him, who is his parent
                if(nodedepth-oldnodedepth == 1) {
                        nodep[nodedepth-1]=oldnode;
                }
                # for debugging
                #printf("%d %s\n", nodedepth, node);
                #printf("\t\"%s\";\n",node);
                # print the vectors
                if (oldnodedepth != -1) {
                        # if need filter or whose parent have been filter, not print it, and set the flat of filter to 1
                        if(need_filter(node) || filternode[nodep[nodedepth-1]]==1) {
                                filter[node]=1;
			} else if (nodep[nodedepth-1] != "") {
                                printf("\t\"%s\" -> \"%s\";\n", nodep[nodedepth-1], node, nodep[nodedepth-1], node);
                        #       printf("\t\"%s\" -> \"%s\"[label=\"%s>%s\"];\n", nodep[nodedepth-1], node, nodep[nodedepth-1], node);
                        }
                }
                # save the old depth and the old node
                oldnodedepth=nodedepth;
                oldnode=node;
        }END{
                printf("}");
        }'

