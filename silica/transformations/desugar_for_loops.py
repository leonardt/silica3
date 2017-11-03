import ast
from silica.ast_utils import *

class ForLoopDesugarer(ast.NodeTransformer):
    def __init__(self):
        super().__init__()
        self.loopvars = set()

    def visit_For(self, node):
        new_body = []
        for s in node.body:
            result = self.visit(s)
            if isinstance(result, list):
                new_body.extend(result)
            else:
                new_body.append(result)
        node.body = new_body
        if is_call(node.iter) and is_name(node.iter.func) and \
           node.iter.func.id == "range":
            # TODO: Support mixed regular and keyword args
            if 4 > len(node.iter.args) > 0:
                assert isinstance(node.target, ast.Name)
                if len(node.iter.args) <= 2:
                    incr = 1
                else:
                    incr = node.iter.args[2].n
                if len(node.iter.args) == 1:
                    start = 0
                    stop = node.iter.args[0]
                else:
                    start = node.iter.args[0].n
                    stop = node.iter.args[1]
            else:
                assert len(node.iter.keywords)
                start = 0
                stop = None
                incr = 1
                for keyword in node.iter.keywords:
                    if keyword.arg == "start":
                        start = keyword.value
                    elif keyword.arg == "stop":
                        stop = keyword.value
                    elif keyword.arg == "step":
                        step = keyword.value
                assert stop is not None
            width = None
            if isinstance(stop, ast.Num):
                width = (stop.n - 1).bit_length()
            else:
                width = None
                for keyword in node.iter.keywords:
                    if keyword.arg == "bit_width":
                        assert isinstance(keyword.value, ast.Num)
                        width = keyword.value.n
                        break
                assert width is not None
            self.loopvars.add((node.target.id, width))
            return [
                ast.Assign([ast.Name(node.target.id, ast.Store())], ast.parse(f"bits({start}, {width})").body[0].value),
                ast.Assign([ast.Name(node.target.id + "_cout", ast.Store())], ast.NameConstant(False)),
                ast.While(ast.parse(f"not_({node.target.id}_cout)").body[0].value,
                    node.body + [
                        ast.parse(f"{node.target.id}, {node.target.id}_cout = add({node.target.id}, bits({incr}, {width}), cout=True)").body[0]
                    ], [])
            ]
        else:  # pragma: no cover
            print_ast(node)
            raise NotImplementedError("Unsupported for loop construct `{}`".format(to_source(node.iter)))

def desugar_for_loops(tree):
    desugarer = ForLoopDesugarer()
    desugarer.visit(tree)
    return tree, desugarer.loopvars
