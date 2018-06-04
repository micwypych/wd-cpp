describe('Student Controller Test', function() {

  beforeEach(module('wd-students'));

  var ctrl;

  beforeEach(inject(function($controller) {
    ctrl = $controller('StudentCtrl');
  }));
  
  it('powinien miec nazwe strony',function() {
    expect(ctrl.pageName).toEqual('Panel Studentów');
  });

  it('powinien miec nazwe strony',function() {
    expect(ctrl.pageName).toEqual('Panel Studentów');
  });
});
